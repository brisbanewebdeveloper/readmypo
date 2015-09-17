## About readmypo

This is PHP Command Line Script to read [Pushover](https://pushover.net/) message via [Pushover API](https://pushover.net/api/client).

## Requirements

This script requires [terminal-notifier](https://github.com/julienXX/terminal-notifier).

You can install it via [Homebrew](http://brew.sh/):
```
brew install terminal-notifier
```

## Usage

#### Register your device (your OSX machine)

Execute the following on terminal (Device Name can be anything like iMac, MacBookPro or MyMacPro):

```shell
readmypo register <Email for Pushover> <Password for Pushover> <Device Name>
```

If it says "name: has already been taken", you need to delete the device at https://pushover.net/.

Above command registers your device and displays the command to read Pushover message.  
The registered device can be seen at: https://pushover.net/

The infomation gets encrypted and saved as ```~/Library/Application Support/readmypo/settings_<Device Name>.txt```.

Example Output:

```shell
Setting is saved to /Users/example/Library/Application Support/readmypo/settings_<Device Name>.txt
To read the message run "readmypo read 12e8a9s08e1sx <Device Name>"   <---- Use this command for next step
```

#### Test if this script can read the message

Execute the following on terminal:

```shell
readmypo read <The key from previous Step> <Device Name>
```

If you see nothing after waiting for about 10 seconds, you need to push something to your device.  
You can send a test message at: https://pushover.net/

This command never finishes.  
To finish the command you press Ctrl + C on terminal.

#### Regsiter the command to keep running with launchd

```shell
cd ~/Library/LaunchAgents
```

Create a file ```~/Library/LaunchAgents/local.readmypo.plist```:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>Label</key>
    <string>local.readmypo</string>
    <key>ProgramArguments</key>
    <array>
        <string>/usr/local/bin/readmypo</string>
        <string>read</string>
        <string><REPLACE HERE TO YOUR KEY></string>
        <string><REPLACE HERE TO YOUR DEVICE NAME></string>
    </array>
</dict>
</plist>
```

Register above service to launchd so that the ```read``` command is automatically launched when you boot your machine.

```shell
launchctl bootstrap gui/$UID local.readmypo.plist
launchctl enable gui/$UID/local.readmypo
launchctl kickstart -k gui/$UID/local.readmypo
```

Open Console.app and keep eye on it.

Example Log:

```
17/09/2015 8:54:10.567 pm php[24196]: Read My PO: /usr/local/bin/terminal-notifier -message 'Example message' -title 'Read MyPO' -open 'http://example.com/example-page.html' -subtitle 'http://example.com/example-page.html'
```

#### I don't like how the message is shown

This script checks if ```~/bin/readmypo``` exists and apply ```require()``` if exists.

- Extend the class ```myCurl```
- Define the method ```onParse()```
- Return the command options for [terminal-notifier](https://github.com/julienXX/terminal-notifier) as Array

That's it.

#### Additional Info

If you have updated the .plist file, you need to do the following on Yosemite:

```shell
launchctl unload local.readmypo.plist
launchctl bootstrap gui/$UID local.readmypo.plist
launchctl enable gui/$UID/local.readmypo
launchctl kickstart -k gui/$UID/local.readmypo
```

The following command kills the current process and re-runs the ```read``` command:

```shell
launchctl kickstart -k gui/$UID/local.readmypo
```

## About readmypo

This is PHP Command Line Script to read [Pushover](https://pushover.net/) message via [Pushover API](https://pushover.net/api/client).

## Requirements

This script requires other command "terminal-notifier".  
If you don't have it and have brew do:  
```
> brew install terminal-notifier
```

## Usage

#### Register your device (your OSX machine)

Execute the following on terminal (Device Name can be anything like iMac, MacBookPro or MyMacPro):

```shell
> readmypo register <Email for Pushover> <Password for Pushover> <Device Name>
```

If it says "name: has already been taken", you need to delete the device at https://pushover.net/.

Above command registers your device and displays the command to read Pushover message.
The registered device can be seen at: https://pushover.net/

The infomation gets encrypted and saved as:  
~/Library/Application Support/readmypo/settings_<Device Name>.txt

Example Output
```shell
Setting is saved to /Users/example/Library/Application Support/readmypo/settings_<Device Name>.txt
To read the message run "readmypo read 12e8a9s08e1sx <Device Name>"   <---- Use this command for next step
```

#### Test if this script can read the message

Execute the following on terminal:

```shell
> readmypo read <The key from Step 2> <Device Name>
```

If you see nothing after waiting for about 10 seconds, you need to push something to your device.
You can send a test message at: https://pushover.net/

This command never finishes.  
To finish the command you press Ctrl + C on terminal.

#### Regsiter the command to keep running with launchd

```shell
> cd ~/Library/LaunchAgents
# Create a file ~/Library/LaunchAgents/local.readmypo.plist:
```

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

```shell
> launchctl bootstrap gui/$UID local.readmypo.plist
> launchctl enable gui/$UID/local.readmypo
> launchctl kickstart -k gui/$UID/local.readmypo

# If key has been changed:
> launchctl unload local.readmypo.plist
> launchctl bootstrap gui/$UID local.readmypo.plist
> launchctl enable gui/$UID/local.readmypo
```

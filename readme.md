## About this script

- Unofficial [Pushover](https://pushover.net/) Client
- PHP Command Line Script to read [Pushover](https://pushover.net/) Message via [Pushover Open Client API](https://pushover.net/api/client) for OSX Environment

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

The infomation gets encrypted and saved as:  
```~/Library/Application Support/readmypo/settings_<Device Name>.txt```

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

Send a test message at: https://pushover.net/

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

This script checks if PHP script file ```~/bin/readmypo``` exists and apply ```require()``` if does.

- Define the class ```myCurlExt``` extending the class ```myCurl```
- Override the method ```parse()```
- Return the command options for [terminal-notifier](https://github.com/julienXX/terminal-notifier) as Array

```php
<?php

class myCurlExt extends myCurl {
    public function parse($data) {
        $args = array();
        $data->message = escapeshellarg($data->message);
        $args[] = "-message {$data->message}"; // escapeshellarg() returns like 'abc 123'
        // Say, you always send "title" parameter
        $data->title = escapeshellarg($data->title);
        $args[] = "-subtitle {$data->title}";
        if (isset($data->url)) {
            $args[] = "-open '{$data->url}'";
        }
        return $args;
    }
}
```

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

## Is this to receive the message for my OSX machine?

Yes, it is. And the following does opposite, sending the message.  

[How to send a notification to Mac OSX computer from iOS device via Workflow and Pushover](https://gist.github.com/hironozu/2b6d1d174dbb13f9ea3d)

## Disclaimer

readmypo is an unofficial Pushover Open Client, and that it is not released or supported by Superblock.

<?php

/*
    If you need to refer the setting:

    - Define the method pluginXXXReadSetting()
      (XXX is the name of your plugin which is "Download" for this plugin).

    - Implement the logic when there is no setting for your plugin.
*/
function pluginDownloadReadSetting($myCurl) {
    if (empty($myCurl->setting->download)) {
        $path = $myCurl->getHomeDirectory() . DIRECTORY_SEPARATOR . 'readmypo_download';
        $myCurl->setting->download = array('path' => $path);
    }
}

/*
    Implementation for the plugin

    - Raw data from Pushover API is passed to $data.
    - You can access to the main class via $myCurl.
*/
function pluginDownload($myCurl, $data) {

    if (strpos($data->title, '!dl') === false) return;

    $rawData = file_get_contents($data->url);

    $path = $myCurl->setting->download['path'];
    if ( ! file_exists($path)) mkdir($path, 0755, true);

    $filename = basename($data->url);
    if ( ! preg_match('/\.[^.]+$/', $filename)) $filename = $data->url;
    $filename = preg_replace('/[^-.0-9a-zA-Z]/', '_', $filename);

    $filePath = $path . DIRECTORY_SEPARATOR . $filename;
    if (file_exists($filePath)) {
        echo "{$data->url} - File exists\n";
        syslog(LOG_NOTICE, PROGRAM . ": Download: {$data->url} - File exists");
    } else {
        file_put_contents($filePath, $rawData);
        echo "Downloaded {$data->url} to {$filePath}\n";
        syslog(LOG_NOTICE, PROGRAM . ": Download: {$data->url} to {$filePath}");
    }
}

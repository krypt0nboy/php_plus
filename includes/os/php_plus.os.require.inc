<?php

/**
 * require_once every file in a directory.
 *
 * @param string $dir
 *   A valid directory path.
 * @param bool   $ved
 *   Whether to validate that the files exist or not.
 * @param string $mask
 *   A regexp to mask a certain type of file.
 * @param array  $options
 *   An array of options to be used with file_scan_directory().
 */
function require_dir_once($dir, $ved = TRUE, $mask = RGX__FILE_EXT_INC, $options = array()) {
  $files = file_scan_directory($dir, $mask, $options);
  /** @var object $file */
  foreach ($files as $file) {
    if ($ved) {
      $exists = file_exists($file->file_uri);
      if ($exists) {
        require_once $file->file_uri;
      }
    }
    else {
      require_once $file->files_uri;
    }
  }
}
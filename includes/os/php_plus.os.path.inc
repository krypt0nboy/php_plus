<?php

/**
 * @file
 *
 * This file provides with path functions.
 */

/**
 * Joins paths together.
 *
 * @param string $head
 *   The head path.
 * @param array  $tails
 *   The tail path elements to join.
 * @param bool   $slash_end
 *   Whether to end with slash or not.
 *
 * @return string
 */
function paths_join($head, array $tails = array(), $slash_end = TRUE) {
  $head_  = clast($head) == '/' ? substr($head, 0, strlen($head) - 1) : $head;
  $tails_ = array();
  foreach ($tails as $tail) {
    foreach (array_filter(explode('/', $tail), 'strlen') as $t) {
      $tails_[] = $t;
    }
  }
  $concat = concat($head_, $tails_, '/');
  if ($slash_end) {
    $path = $concat . (clast($concat) == '/' ? '' : '/');
  }
  else {
    $path = clast($concat) == '/' ? substr($concat, 0, strlen($concat - 1)) : $concat;
  }

  return $path;
}

/**
 * Builds and returns a file path using a file name, path and extension.
 *
 * @param string      $file_name
 *   The file name.
 * @param string      $head
 *   The path head element.
 * @param array       $tails
 *   The path tails elements.
 * @param null|string $file_ext
 *   The file extension (optional), without the "." (dot) prefix.
 *   If not provided, it must be already included in the file name.
 *
 * @return string
 */
function file_path($file_name, $head, array $tails = array(), $file_ext = NULL) {
  $path  = !empty($tails) ? paths_join($head, $tails) : $head;
  $file  = isset($file_ext) ? concat($file_name, $file_ext, '.') : $file_name;
  $file_ = $path . $file;

  return $file_;
}

/**
 * Splits the pathname into a pair (head, tail).
 *
 * @param string $path
 *   The path to split.
 *
 * @return array
 */
function path_split($path) {
}

/**
 * Returns the head part of a path.
 *
 * @param string $path
 *   The path to split.
 *
 * @return string
 */
function path_head($path) {
  $split = explode('/', $path);

  return end($split);
}

/**
 * Returns the path's head position.
 *
 * @param string $path
 *   The path to split.
 *
 * @return string
 */
function path_head_pos($path) {
  $split = array_filter(explode('/', $path), 'strlen');

  return count($split) - 1;
}
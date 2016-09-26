<?php

/**
 * @file
 *
 * This file provides with parsing functions.
 */

/**
 * Parses a php file.
 *
 * @param string $file
 *   A file valid path.
 *
 * @return array
 */
function parse_php_file($file) {
  $content    = file_get_contents($file);
  $classes    = extract_classes($content);
  $traits     = extract_traits($content);
  $interfaces = extract_interfaces($content);
  $parsed     = array(
    'classes'    => !empty($classes) ? $classes : array(),
    'traits'     => !empty($traits) ? $traits : array(),
    'interfaces' => !empty($interfaces) ? $interfaces : array(),
  );

  return $parsed;
}

/**
 * Extracts the classes of a php file.
 *
 * @param string $file_content
 *   The file content.
 *
 * @return array
 */
function extract_classes($file_content) {
  $tokens  = token_get_all($file_content);
  $classes = array();
  //@todo code borrowed to modify with my own.
  for ($i = 2; $i < count($tokens); $i++) {
    if ($tokens[$i - 2][0] == T_CLASS
        && $tokens[$i - 1][0] == T_WHITESPACE
        && $tokens[$i][0] == T_STRING
    ) {
      $classes[] = $tokens[$i][1];
    }
  }

  //@todo code borrowed to modify with my own end.

  return $classes;
}

/**
 * Extracts the traits of a php file.
 *
 * @param string $file_content
 *   The file content.
 *
 * @return array
 */
function extract_traits($file_content) {
  $tokens = token_get_all($file_content);
  $traits = array();
  //@todo code borrowed to modify with my own.
  for ($i = 2; $i < count($tokens); $i++) {
    if ($tokens[$i - 2][0] == T_TRAIT
        && $tokens[$i - 1][0] == T_WHITESPACE
        && $tokens[$i][0] == T_STRING
    ) {
      $traits[] = $tokens[$i][1];
    }
  }

  //@todo code borrowed to modify with my own end.

  return $traits;
}

/**
 * Extracts the interfaces of a php file.
 *
 * @param string $file_content
 *   The file content.
 *
 * @return array
 */
function extract_interfaces($file_content) {
  $tokens     = token_get_all($file_content);
  $interfaces = array();
  //@todo code borrowed to modify with my own.
  for ($i = 2; $i < count($tokens); $i++) {
    if ($tokens[$i - 2][0] == T_INTERFACE
        && $tokens[$i - 1][0] == T_WHITESPACE
        && $tokens[$i][0] == T_STRING
    ) {
      $interfaces[] = $tokens[$i][1];
    }
  }

  //@todo code borrowed to modify with my own end.

  return $interfaces;
}
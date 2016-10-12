<?php

/**
 * @file
 *
 * This file provides with useful regex expressions and functions.
 */

/**
 * Regexp to match a regular expression.
 */
define('RGX__REGEXP', '/\/.*\//');
/**
 * Regexp to match an array var type.
 */
define('RGX__PHPDOC_ARRAY', '/^\w+\[\]$/');
/**
 * Regexp to match a phpdoc multi type.
 */
define('RGX__PHPDOC_MULTI', '/(?P<arrays>\w+\[\])|(?P<single>\w+)/');
/**
 * Regexp to match and catch phpdoc multi type.
 */
define('RGX__CATCH__PHPDOC_MULTI', '/(?P<arrays>\w+\[\])|(?P<single>\w+)/');
/**
 * Regexp to match an class.
 */
define('RGX__CLASS', '/^[a-zA-Z_\x7f-\xff][a-zA-Z0-9_\x7f-\xff]*$/');
/**
 * Regexp to match an array of classes.
 */
define('RGX__CLASS_ARRAY', '/^[a-zA-Z_\x7f-\xff][a-zA-Z0-9_\x7f-\xff]*\[\]$/');
/**
 * Regexp to match a non regular expression.
 */
define('RGX__NOREGEXP', '/^\w+/');
/**
 * Regexp to match a file with extension ".inc".
 */
define('RGX__FILE_EXT_INC', '/.*.inc$/');
/**
 * Regex to match a "wildcard" and store it in $matches['wildcards'].
 */
define('RGX__CATCH__WILDCARD', '/(?P<wildcards>%\w+%)/');
/**
 * Regex to match a "wildcard" and store it in $matches['wildcards'].
 */
define('RGX__CATCH__WILDCARD_SUB', '/(%(?P<wildcards>\w+)%)/');
/**
 * Regex to match a "wildcard".
 */
define('RGX__WILDCARD', '/(%\w+%)/');
/**
 * Regex to match a file name with an extension.
 */
define('RGX__FILE_EXT', '/^\w+.\w+$/');
/**
 * Regex to match and catch a file name extension.
 */
define('RGX__CATCH__FILE_EXT', '/^\w+.(?P<ext>\w+)$/');

/**
 * Matches a string vs an array of regular expressions.
 *
 * @param string $needle
 *   The needle to match in the regex array.
 * @param array  $array
 *   The array to check.
 * @param bool   $ensure
 *   Whether to make sure each array value is a regexp.
 *   If FALSE, the array value will be formatted as one.
 *
 * @return array
 */
function preg_grep_reverse($needle, array $array = array(), $ensure = FALSE) {
  $array   = $ensure ? preg_grep('/\/.*\//', $array) : arr2rgxp($array);
  $matches = array();
  foreach ($array as $rgx) {
    $match = preg_match($rgx, $needle);
    if ($match) {
      $matches[] = $rgx;
    }
  }

  return $matches;
}

/**
 * Removes any matching characters from a string.
 *
 * @param string $pattern
 *   The pattern to match. A valid regexp.
 * @param string $string
 *   The string to process.
 *
 * @return string
 */
function preg_remove($pattern, $string) {
  return preg_replace($pattern, '', $string);
}
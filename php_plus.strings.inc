<?php

/**
 * @file
 *
 * This file contains functions to format data.
 */

/**
 * Transforms a string into a camel style string.
 * (Eg : "foo_bar foo" turns to "FooBarFoo").
 *
 * @param string $string
 *   The string to transform.
 * @param bool   $uc_first
 *   Whether to uc first or not.
 *
 * @return string
 */
function str2camelcase($string, $uc_first = TRUE) {
  $regexp = '/(?P<matches>[^a-zA-Z0-9]+)/';
  preg_match_all($regexp, $string, $matches, PREG_OFFSET_CAPTURE);
  $index_mod = 0;
  foreach ($matches['matches'] as $match) {
    $char        = $match[0];
    $length      = strlen($char);
    $pos         = $match[1] - $index_mod;
    $follow      = substr($string, ($pos + $length), 1);
    $to_rep_with = preg_match('/[[:lower:]]/', $follow) ? ucfirst($follow) : $follow;
    $string      = substr_replace($string, $to_rep_with, $pos, ($length + 1));
    $index_mod += $length;
  }

  return $uc_first ? ucfirst($string) : $string;
}

/**
 * Transforms the entity_type machine_name into the entity class name.
 * (Eg : "FooBar" turns to "foo_bar").
 *
 * @param $string
 *   The string.
 *
 * @return string
 */
function camelcase2lowercase($string) {
  $regexp = '/(?P<upper>[A-Z])/';
  preg_match_all($regexp, $string, $matches, PREG_OFFSET_CAPTURE);
  $index_mod = 0;
  foreach ($matches['upper'] as $match) {
    $upper         = $match[0];
    $pos           = $match[1] + $index_mod;
    $upper_replace = $pos == 0 ? $upper : '_' . $upper;
    if ($pos != 0) {
      $pos--;
    }
    $string = substr_replace($string, $upper_replace, $pos, 1);
    $index_mod++;
  }

  return strtolower($string);
}

/**
 * Formats a word from single to plural.
 *
 * @param string $word
 *   The word to format.
 *
 * @return string
 */
function single2plural($word) {
  switch (substr($word, (strlen($word) - 1), 1)) {
    case 's':
      return $word . 'es';
      break;
    case 'y':
      return substr_replace($word, 'ies', (strlen($word) - 1), 1);
      break;
    default:
      return $word . 's';
      break;
  }
}

/**
 * Formats a string to a valid regular expression.
 *
 * @param string $string
 *   The string to transform.
 *
 * @return string
 */
function str2rgxp($string) {
  //@todo actually handle regex conversion.
  return '/' . $string . '/';
}

/**
 * Formats array values to regular expressions.
 *
 * @param array $array
 *   The array to format.
 *
 * @return array
 */
function arr2rgxp(array $array = array()) {
  $no_matches = preg_grep(RGX__NOREGEXP, $array);
  $match      = preg_grep(RGX__REGEXP, $array);
  $fix        = array_map('str2rgxp', $no_matches);

  return $fix + $match;
}

/**
 * Concatenates the values of an array.
 *
 * @param string       $str
 *   The array containing the string to concatenate.
 * @param string|array $arg
 *   The strings to concatenate.
 * @param string|int   $lnk
 *   The character to use for concatenation.
 *
 * @return string
 */
function concat($str, $arg, $lnk = '_') {
  $concat = $str;
  switch (gettype($arg)) {
    case 'int':
    case 'string':
      $concat .= $lnk . $arg;
      break;
    case 'array':
      for ($i = 0; $i < count($arg); $i++) {
        $concat .= $lnk . $arg[$i];
      }
      break;
    default:
      break;
  }

  return $concat;
}

/**
 * Returns the last character of a string.
 *
 * @param string $string
 *   The string to evaluates.
 *
 * @return string
 */
function clast($string) {
  return substr($string, strlen($string), 1);
}

/**
 * Returns the first character of a string.
 *
 * @param string $string
 *   The string to evaluates.
 *
 * @return string
 */
function cfirst($string) {
  return substr($string, 0, 1);
}
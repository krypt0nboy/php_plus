<?php

/**
 * Replace a matching wildcard with a replace pattern.
 *
 * @param string $string
 *   The string to process.
 * @param array  $wildcards
 *   The wildcard to replace.
 * @param array  $variables
 *   The replacing variables.
 *
 * @return mixed
 */
function tpl_process_wildcards($string, $wildcards = array(), $variables) {
  for ($i = 0; $i < count($wildcards); $i++) {
    $varname = str_replace('%', '', $wildcards[$i]);
    $rgx     = '/' . $wildcards[$i] . '/';
    if (isset($variables[$varname])) {
      $var = $variables[$varname];
      switch (gettype($var)) {
        default:
          $string = preg_replace($rgx, $var, $string);
          break;
      }
      $matches = tpl_extract_wildcard($var);
      if (!empty($matches)) {
        for ($ii = 0; $ii < count($matches); $ii++) {
          $var_n = str_replace('%', '', $matches[$ii]);
          if (isset($variables[$var_n])) {
            $rgx_n  = '/' . $matches[$ii] . '/';
            $string = preg_replace($rgx_n, $variables[$var_n], $string);
          }
        }
      }
    }
  }

  return $string;
}

/**
 * Extracts the wildcards from a template string.
 *
 * @param string $string
 *   The template string.
 *
 * @return array
 */
function tpl_extract_wildcard($string) {
  preg_match_all(RGX__CATCH__WILDCARD, $string, $matches);

  return $matches['wildcards'];
}

/**
 * Process a string template.
 *
 * @param string $string
 *   The template string to process.
 * @param array  $variables
 *   The array of replacing variables.
 *
 * @return string
 */
function tpl_process($string, $variables = array()) {
  $wildcards = tpl_extract_wildcard($string);

  return tpl_process_wildcards($string, $wildcards, $variables);
}

/**
 * Evaluates if a string is a template and requires to be processed.
 *
 * @param string $string
 *   The string to evaluate.
 *
 * @return bool
 */
function str_is_tpl($string) {
  return preg_match(RGX__WILDCARD, $string);
}
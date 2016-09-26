<?php

/**
 * @file
 *
 * This file contains functions to work with arrays.
 */

/**
 * Recursive equivalent of array_values.
 *
 * @param array $array
 *   The array to extract the values from.
 *
 * @return array
 */
function array_values_recursive(array $array = array()) {
  $values = array();
  foreach (array_values($array) as $value) {
    if (is_array($value)) {
      foreach ($value as $val) {
        $values[] = is_array($val) ? array_values_recursive($val) : $val;
      }
    }
    else {
      $values[] = $value;
    }
  }

  return $values;
}

/**
 * Returns the variable type for each key value in an array.
 *
 * @param array $array
 *   The array to check.
 *
 * @return array
 */
function array_values_gettype(array $array = array()) {
  $types = array();
  foreach ($array as $key => $value) {
    $types[$key] = gettype($value);
  }

  return $types;
}

/**
 * Returns the unique variable types of an array values.
 *
 * @param array   $array
 *   The array to check.
 * @param boolean $reset
 *   Set TRUE to get the first unique item only.
 *
 * @return string|string[]
 *   An array of strings matching existing php variable types.
 *
 * @see php_vars().
 */
function array_values_gettype_unique(array $array = array(), $reset = TRUE) {
  $uniques = array_unique(array_values_gettype($array));

  return isset($reset) ? reset($uniques) : $uniques;
}

/**
 * Evaluates if an array is recursive.
 *
 * @param array $array
 *   The array to evaluate.
 *
 * @return bool
 */
function is_array_recursive(array $array = array()) {
  return count(array_filter(array_values($array), 'is_array')) >= 1;
}

/**
 * Evaluates if an array is associative.
 *
 * @param array $array
 *   The array to evaluate.
 *
 * @return bool
 */
function is_array_associative(array $array = array()) {
  return count(array_filter(array_keys($array), 'is_string')) > 0;
}

/**
 * Evaluates if an array is sequential.
 *
 * @param array $array
 *   The array to evaluate.
 *
 * @return bool
 */
function is_array_sequential(array $array = array()) {
  return count(array_filter(array_keys($array), 'is_string')) == 0;
}

/**
 * Checks if an array values are numeric.
 *
 * @param array $array
 *   The array to check.
 *
 * @return bool
 */
function is_array_numeric(array $array = array()) {
  $eval = array();
  foreach (array_values_gettype($array) as $key => $item) {
    $eval[] = is_numeric($item);
  }

  return in_array(TRUE, $eval, TRUE);
}

/**
 * Checks if an array values are all booleans.
 *
 * @param array $array
 *   The array to check.
 *
 * @return bool
 */
function is_array_booleans(array $array = array()) {
  return array_values_gettype_unique($array) == 'boolean';
}

/**
 * Checks if an array values are all nulls.
 *
 * @param array $array
 *   The array to check.
 *
 * @return bool
 */
function is_array_nulls(array $array = array()) {
  return in_array(NULL, $array, TRUE);
}

/**
 * Checks if an array values are all FALSE booleans.
 *
 * @param array $array
 *   The array to check.
 *
 * @return bool
 */
function is_array_false(array $array = array()) {
  return in_array(FALSE, $array, TRUE);
}

/**
 * Checks if an array values are all TRUE booleans.
 *
 * @param array $array
 *   The array to check.
 *
 * @return bool
 */
function is_array_true(array $array = array()) {
  return in_array(TRUE, $array, TRUE);
}

/**
 * Checks if an array values are all strings.
 *
 * @param array $array
 *   The array to check.
 *
 * @return bool
 */
function is_array_strings(array $array = array()) {
  return array_values_gettype_unique($array) == 'string';
}

/**
 * Checks if an array values are all integers.
 *
 * @param array $array
 *   The array to check.
 *
 * @return bool
 */
function is_array_integers(array $array = array()) {
  return array_values_gettype_unique($array) == 'integer';
}

/**
 * Checks if an array values are all doubles.
 *
 * @param array $array
 *   The array to check.
 *
 * @return bool
 */
function is_array_doubles(array $array = array()) {
  return array_values_gettype_unique($array) == 'double';
}

/**
 * Checks if an array values are all objects.
 *
 * @param array $array
 *   The array to check.
 *
 * @return bool
 */
function is_array_objects(array $array = array()) {
  return array_values_gettype_unique($array) == 'object';
}

/**
 * Checks if an array values are all callable functions.
 *
 * @param array $array
 *   The array to check.
 *
 * @return bool
 */
function is_array_callable(array $array = array()) {
  $eval = array();
  foreach (array_values_gettype($array) as $key => $item) {
    $eval[] = is_callable($item);
  }

  return in_array(TRUE, $eval, TRUE);
}

/**
 * Checks if an array values are objects of a given class.
 *
 * @param array $array
 *   The array to check.
 * @param       $class
 *   The class to check.
 *
 * @return bool
 */
function is_array_objects_of(array $array = array(), $class) {
  $eval = array();
  foreach ($array as $key => $item) {
    $eval[] = is_object($item) && is_a($item, $class);
  }

  return in_array(TRUE, $eval, TRUE);
}

/**
 * Flattens an array values.
 *
 * @param array       $array
 *   The array to flatten.
 * @param null|string $parent_key
 *   The parent key.
 *
 * @return array
 */
function flatten_array(array $array = array(), $parent_key = NULL) {
  $flat = array();
  foreach ($array as $key => $item) {
    $new_key = isset($parent_key) ? concat($parent_key, $key) : $key;
    if (is_array($item)) {
      $flat += flatten_array($item, $new_key);
    }
    else {
      $flat[$new_key] = $item;
    }
  }

  return $flat;
}
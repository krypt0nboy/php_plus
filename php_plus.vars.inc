<?php

/**
 * @file
 *
 * This file provides with variable type related functions.
 */

/**
 * Returns the existing php variable types.
 *
 * @return string[]
 */
function php_vars() {
  return array(
    'boolean',
    'integer',
    'double',
    'string',
    'array',
    'object',
    'resource',
    'NULL',
  );
}

/**
 * Returns php var types validation functions.
 *
 * @return array
 */
function php_vars_match_functions() {
  return array(
    'boolean'  => 'is_bool',
    'integer'  => 'is_integer',
    'double'   => 'is_double',
    'string'   => 'is_string',
    'array'    => 'is_array',
    'object'   => 'is_object',
    'resource' => 'is_resource',
    'NULL'     => 'is_null',
  );
}

/**
 * Returns the var types handled by php_plus.
 *
 * @return array
 */
function phpdoc_vars() {
  return array(
    'primitives' => array(
      'string',
      'int',
      'integer',
      'float',
      'bool',
      'boolean',
      'array',
      'resource',
      'null',
      'callable',
    ),
    'keywords'   => array(
      'mixed',
      'void',
      'object',
      'false',
      'true',
      'self',
      'static',
      '$this',
      RGX__CLASS
    ),
    'arrays'     => array(
      'string[]',
      'int[]',
      'integer[]',
      'float[]',
      'bool[]',
      'boolean[]',
      'array[]',
      'resource[]',
      'null[]',
      'callable[]',
      'mixed[]',
      'void[]',
      'object[]',
      'false[]',
      'true[]',
      'self[]',
      'static[]',
      '$this[]',
      RGX__CLASS_ARRAY
    ),
    'multitypes' => array(
      //@todo add regex to handle multi types.
      '//'
    )
  );
}

/**
 * Returns the var types handled by php_plus.
 *
 * @return array
 */
function php_plus_vars() {
  return array(
    'keywords' => array(
      'regexp',
    )
  );
}

/**
 * Returns the extracted types of a multitype value keyword.
 *
 * (Eg : "int|null" will return an array containing "int", "null").
 *
 * @param string $multitypes
 *   The multitypes as a string.
 *
 * @return string[]
 */
function multitypes_extract($multitypes) {
  return explode('|', $multitypes);
}

/**
 * Evaluates if a var type is a php variable type.
 *
 * @param string $type
 *   The type to evaluate.
 *
 * @return bool
 */
function is_of_php($type) {
  return in_array($type, php_vars());
}

/**
 * Evaluates if a var type is a variable type or keyword issued by phpdoc.
 *
 * @param string $type
 *
 * @return bool
 */
function is_of_php_doc($type) {
  if (!is_of_php($type)) {
    $phpdoc   = array_values(phpdoc_vars());
    $preg_rev = preg_grep_reverse($phpdoc);

    return !empty($preg_rev);
  }
  else {
    return FALSE;
  }
}

/**
 * Returns the group of a var type from php_doc vars.
 *
 * @param string $type
 *   The type to evaluate.
 *
 * @return string
 */
function var_type_get_group($type) {}

/**
 * Checks if a value matches a variable type.
 * The variable type refers to non stricty php variables.
 *
 * (Eg : value_match_type(1235.568, 'numeric') will return TRUE.)
 *
 * @param mixed  $var
 *   The var to match.
 * @param string $type
 *   The type to match.
 *
 * @return bool
 */
function value_match_type($var, $type) {}
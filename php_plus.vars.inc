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
    'bool',
    'integer',
    'int',
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
    'bool'     => 'is_bool',
    'integer'  => 'is_integer',
    'int'      => 'is_integer',
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
      'string'   => 'string',
      'int'      => 'int',
      'integer'  => 'integer',
      'float'    => 'float',
      'bool'     => 'bool',
      'boolean'  => 'boolean',
      'array'    => 'array',
      'resource' => 'resource',
      'null'     => 'null',
      'callable' => 'callable',
    ),
    'keywords'   => array(
      'mixed'    => 'mixed',
      'void'     => 'void',
      'object'   => 'object',
      'false'    => 'false',
      'true'     => 'true',
      'self'     => 'self',
      'static'   => 'static',
      'numeric'  => 'numeric',
      '$this'    => '$this',
      'class'    => RGX__CLASS,
      RGX__CLASS => RGX__CLASS,
    ),
    'arrays'     => array(
      'string[]'       => 'string[]',
      'int[]'          => 'int[]',
      'integer[]'      => 'integer[]',
      'float[]'        => 'float[]',
      'bool[]'         => 'bool[]',
      'boolean[]'      => 'boolean[]',
      'array[]'        => 'array[]',
      'resource[]'     => 'resource[]',
      'null[]'         => 'null[]',
      'callable[]'     => 'callable[]',
      'mixed[]'        => 'mixed[]',
      'void[]'         => 'void[]',
      'object[]'       => 'object[]',
      'false[]'        => 'false[]',
      'true[]'         => 'true[]',
      'self[]'         => 'self[]',
      'static[]'       => 'static[]',
      'numeric[]'      => 'numeric[]',
      '$this[]'        => '$this[]',
      'class[]'        => RGX__CLASS_ARRAY,
      RGX__CLASS_ARRAY => RGX__CLASS_ARRAY,
    )
  );
}

/**
 * @return array
 */
function phpdoc_vars_match_functions() {
  return array(
    'false'          => 'is_false',
    'true'           => 'is_true',
    'class'          => '',
    RGX__CLASS       => '',
    RGX__CLASS_ARRAY => '',
  );
}

/**
 * Returns the extracted types of a multitype value keyword.
 *
 * (Eg : "int|null" will return an array containing "int", "null").
 *
 * @param string $type
 *   The multitypes as a string.
 *
 * @return string[]
 */
function multitypes_extract($type, $organized = FALSE) {
  preg_match_all(RGX__CATCH__PHPDOC_MULTI, $type, $matches);
  $arrays = array_filter($matches['arrays'], 'strlen');
  $single = array_filter($matches['single'], 'strlen');

  return $organized ? array(
    'arrays' => $arrays,
    'single' => $single
  ) : $arrays + $single;
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
    $phpdoc   = array_values(array_values(phpdoc_vars()));
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
function var_type_get_group($type) {
}

/**
 * Returns the possible phpdoc type for a variable.
 *
 * @param mixed $var
 *   The var to evaluate.
 *
 * @return string[]
 */
function var_gettypes($var) {
  $type = gettype($var);
}

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
function value_match_type($var, $type) {
  if ($type == 'mixed') {
    return TRUE;
  }
  else {
    return !preg_match(RGX__PHPDOC_MULTI, $type) ? value_match_type_nonmulti($var, $type) : value_match_type_multi($var, $type);
  }
}

/**
 * Checks if a value matches a variable type that is not of type multittype.
 *
 * @param mixed  $var
 *   The var to match.
 * @param string $type
 *   The type to match.
 *
 * @return bool
 */
function value_match_type_nonmulti($var, $type) {
  if (is_of_php($type)) {
    return value_match_php_type($var, $type);
  }
  else {
    return preg_match(RGX__PHPDOC_ARRAY, $type) ? value_match_type_array($var, $type) : value_match_type_nonarray($var, $type);
  }
}

/**
 * Checks if a value matches a variable type that is of type multitypes.
 *
 * @param mixed  $var
 *   The var to match.
 * @param string $type
 *   The types to match. (as string).
 *
 * @return bool
 */
function value_match_type_multi($var, $type) {
  $evals = array();
  $types = array_values(multitypes_extract($type));
  foreach ($types as $t) {
    $evals[] = value_match_type_nonmulti($var, $t);
  }

  return in_array(TRUE, $evals);
}

/**
 * Checks if a value matches a variable type that is of type array[].
 *
 * @param mixed  $var
 *   The var to match.
 * @param string $type
 *   The types to match. (as string).
 *
 * @return bool
 */
function value_match_type_array($var, $type) {
  $clean = preg_replace('/\[\]/', '', $type);
  if (is_of_php($clean)) {
    return array_values_match_php_type($var, $clean);
  }
  else {
    $evals = array();
    foreach ($var as $item) {
      $evals[] = value_match_type_nonarray($item, $clean);
    }

    return in_array(TRUE, $evals);
  }
}

/**
 * Checks if a value matches a variable type that is not of type array[].
 *
 * @param mixed  $var
 *   The var to match.
 * @param string $type
 *   The types to match. (as string).
 *
 * @return bool
 */
function value_match_type_nonarray($var, $type) {
  $pseudo_type = preg_match(RGX__CLASS, $type) && $type != 'class' ? 'class_instance' : $type;
  switch ($pseudo_type) {
    case 'false':
    case 'true':
      return $type == 'false' ? ($var === FALSE) : ($var === TRUE);
      break;
    case 'class':
      return preg_match(RGX__CLASS, $var);
      break;
    case 'class_instance':
      return is_a($var, $type);
      break;
    case 'numeric':
      return is_numeric($var);
      break;
  }
}

/**
 * Checks if a value matches a variable type that is a php type.
 *
 * @param mixed  $var
 *   The var to match.
 * @param string $type
 *   The types to match. (as string).
 *
 * @return bool
 */
function value_match_php_type($var, $type) {
  $callback = php_vars_match_functions()[$type];

  return $callback($var);
}

/**
 * Checks if a value matches a variable type that is a php type.
 *
 * @param mixed  $var
 *   The var to match.
 * @param string $type
 *   The types to match. (as string).
 *
 * @return bool
 */
function array_values_match_php_type($var, $type) {
  $callback = php_vars_match_functions()[$type];
  $evals    = array();
  foreach ($var as $item) {
    $evals[] = $callback($item);
  }

  return !in_array(FALSE, $evals, TRUE);
}

/**
 * Evaluates if a var matches a class pattern.
 *
 * @param mixed $var
 *   The var to evaluate.
 *
 * @return bool
 */
function is_class($var) {
  return preg_match(RGX__CLASS, $var);
}

/**
 * Returns TRUE is empty.
 *
 * @param mixed $var
 *   The var to evaluate.
 *
 * @return bool
 */
function is_empty($var) {
  return empty($var);
}
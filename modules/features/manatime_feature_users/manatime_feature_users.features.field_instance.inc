<?php
/**
 * @file
 * manatime_feature_users.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function manatime_feature_users_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_weekly_hours'.
  $field_instances['user-user-field_weekly_hours'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => 1,
          'scale' => 2,
          'thousand_separator' => '',
        ),
        'type' => 'number_decimal',
        'weight' => 0,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => 1,
          'scale' => 2,
          'thousand_separator' => '',
        ),
        'type' => 'number_decimal',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'fences_wrapper' => 'div',
    'field_name' => 'field_weekly_hours',
    'label' => 'Weekly hours',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => 0,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 11,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Weekly hours');

  return $field_instances;
}

<?php
/**
 * @file
 * manatime_feature_timesheet_reminder.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function manatime_feature_timesheet_reminder_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'message-timesheet_reminder-field_user'.
  $field_instances['message-timesheet_reminder-field_user'] = array(
    'bundle' => 'timesheet_reminder',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
      'message_notify_email_body' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'message_notify_email_subject' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'message',
    'fences_wrapper' => 'div',
    'field_name' => 'field_user',
    'label' => 'User',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('User');

  return $field_instances;
}

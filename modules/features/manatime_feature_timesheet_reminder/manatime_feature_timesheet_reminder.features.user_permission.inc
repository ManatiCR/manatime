<?php
/**
 * @file
 * manatime_feature_timesheet_reminder.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function manatime_feature_timesheet_reminder_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'manage timesheet reminder'.
  $permissions['manage timesheet reminder'] = array(
    'name' => 'manage timesheet reminder',
    'roles' => array(),
    'module' => 'manatime_feature_timesheets',
  );

  return $permissions;
}

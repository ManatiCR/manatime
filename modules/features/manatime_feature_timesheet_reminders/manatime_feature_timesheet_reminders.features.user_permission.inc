<?php
/**
 * @file
 * manatime_feature_timesheet_reminders.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function manatime_feature_timesheet_reminders_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'manage timesheet reminder'.
  $permissions['manage timesheet reminder'] = array(
    'name' => 'manage timesheet reminder',
    'roles' => array(
      'administrator' => 'administrator',
      'super admin' => 'super admin',
    ),
    'module' => 'manatime_feature_timesheets',
  );

  return $permissions;
}

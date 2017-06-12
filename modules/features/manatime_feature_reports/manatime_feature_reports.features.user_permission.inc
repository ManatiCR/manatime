<?php
/**
 * @file
 * manatime_feature_reports.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function manatime_feature_reports_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'See and export reports'.
  $permissions['See and export reports'] = array(
    'name' => 'See and export reports',
    'roles' => array(
      'administrator' => 'administrator',
      'super admin' => 'super admin',
    ),
    'module' => 'manatime_feature_reports',
  );

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'administrator' => 'administrator',
      'super admin' => 'super admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'administrator' => 'administrator',
      'super admin' => 'super admin',
    ),
    'module' => 'user',
  );

  return $permissions;
}

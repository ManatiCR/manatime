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

  // Exported permission: 'See and export reports reports'.
  $permissions['See and export reports reports'] = array(
    'name' => 'See and export reports reports',
    'roles' => array(
      'administrator' => 'administrator',
      'super admin' => 'super admin',
    ),
    'module' => 'manatime_feature_reports',
  );

  return $permissions;
}

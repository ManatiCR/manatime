<?php
/**
 * @file
 * manatime_feature_reports.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function manatime_feature_reports_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 3,
  );

  return $roles;
}

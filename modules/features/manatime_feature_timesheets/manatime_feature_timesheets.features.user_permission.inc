<?php
/**
 * @file
 * manatime_feature_timesheets.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function manatime_feature_timesheets_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'collaborator' => 'collaborator',
      'super admin' => 'super admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create time_entries content'.
  $permissions['create time_entries content'] = array(
    'name' => 'create time_entries content',
    'roles' => array(
      'collaborator' => 'collaborator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create timesheet content'.
  $permissions['create timesheet content'] = array(
    'name' => 'create timesheet content',
    'roles' => array(
      'collaborator' => 'collaborator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own time_entries content'.
  $permissions['delete own time_entries content'] = array(
    'name' => 'delete own time_entries content',
    'roles' => array(
      'collaborator' => 'collaborator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own time_entries content'.
  $permissions['edit own time_entries content'] = array(
    'name' => 'edit own time_entries content',
    'roles' => array(
      'collaborator' => 'collaborator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own timesheet content'.
  $permissions['edit own timesheet content'] = array(
    'name' => 'edit own timesheet content',
    'roles' => array(
      'collaborator' => 'collaborator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'collaborator' => 'collaborator',
      'super admin' => 'super admin',
    ),
    'module' => 'node',
  );

  return $permissions;
}

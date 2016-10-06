<?php
/**
 * @file
 * manatime_feature_timesheets.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function manatime_feature_timesheets_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'timesheet';
  $page->task = 'page';
  $page->admin_title = 'Timesheet';
  $page->admin_description = '';
  $page->path = 'timesheet';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_timesheet__panel';
  $handler->task = 'page';
  $handler->subtask = 'timesheet';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Timesheet',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(
      0 => array(
        'identifier' => 'User',
        'keyword' => 'user',
        'name' => 'user',
        'type' => 'current',
        'uid' => '',
        'id' => 1,
      ),
    ),
    'relationships' => array(
      0 => array(
        'identifier' => 'Timesheet node',
        'keyword' => 'node',
        'name' => 'timesheet_node',
        'context' => 'context_user_1',
        'id' => 1,
      ),
    ),
    'name' => 'panel',
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '44ada62b-577b-4c47-b5d1-1fc0dd7f3a81';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'page_timesheet__panel';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-70d3a00e-4785-4fba-8999-2a28ef9de33f';
  $pane->panel = 'middle';
  $pane->type = 'node_title';
  $pane->subtype = 'node_title';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'link' => 0,
    'markup' => 'none',
    'id' => '',
    'class' => '',
    'context' => 'relationship_timesheet_node_1',
    'override_title' => 1,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '70d3a00e-4785-4fba-8999-2a28ef9de33f';
  $display->content['new-70d3a00e-4785-4fba-8999-2a28ef9de33f'] = $pane;
  $display->panels['middle'][0] = 'new-70d3a00e-4785-4fba-8999-2a28ef9de33f';
  $pane = new stdClass();
  $pane->pid = 'new-e816e2c9-832c-42e6-998e-737cd8fb0e63';
  $pane->panel = 'middle';
  $pane->type = 'timesheet_view';
  $pane->subtype = 'timesheet_view';
  $pane->shown = TRUE;
  $pane->access = array(
    'logic' => 'and',
  );
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'e816e2c9-832c-42e6-998e-737cd8fb0e63';
  $display->content['new-e816e2c9-832c-42e6-998e-737cd8fb0e63'] = $pane;
  $display->panels['middle'][1] = 'new-e816e2c9-832c-42e6-998e-737cd8fb0e63';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['timesheet'] = $page;

  return $pages;

}

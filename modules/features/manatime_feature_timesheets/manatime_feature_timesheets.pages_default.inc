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
  $page->path = 'timesheet/!dates';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array(
    'dates' => array(
      'id' => 1,
      'identifier' => 'dates',
      'name' => 'string',
      'settings' => array(
        'use_tail' => 0,
      ),
    ),
  );
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
      1 => array(
        'identifier' => 'String',
        'keyword' => 'string',
        'name' => 'string',
        'string' => '%dates',
        'id' => 1,
      ),
    ),
    'relationships' => array(
      0 => array(
        'identifier' => 'Timesheet node',
        'keyword' => 'node',
        'name' => 'timesheet_node',
        'context' => array(
          0 => 'context_user_1',
          1 => 'argument_string_1',
        ),
        'id' => 1,
      ),
    ),
    'name' => 'panel',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'dates_access',
          'settings' => NULL,
          'context' => array(
            0 => 'argument_string_1',
          ),
          'not' => TRUE,
        ),
      ),
      'logic' => 'and',
    ),
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
  $pane->pid = 'new-ed262fb1-9e5c-47d7-87fc-03abb0e419b7';
  $pane->panel = 'middle';
  $pane->type = 'node_title';
  $pane->subtype = 'node_title';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'link' => 1,
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
  $pane->uuid = 'ed262fb1-9e5c-47d7-87fc-03abb0e419b7';
  $display->content['new-ed262fb1-9e5c-47d7-87fc-03abb0e419b7'] = $pane;
  $display->panels['middle'][0] = 'new-ed262fb1-9e5c-47d7-87fc-03abb0e419b7';
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
  $pane = new stdClass();
  $pane->pid = 'new-2959f4ed-c2b8-4c69-926b-afba6cbd5ad0';
  $pane->panel = 'middle';
  $pane->type = 'previous_timesheet';
  $pane->subtype = 'previous_timesheet';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '2959f4ed-c2b8-4c69-926b-afba6cbd5ad0';
  $display->content['new-2959f4ed-c2b8-4c69-926b-afba6cbd5ad0'] = $pane;
  $display->panels['middle'][2] = 'new-2959f4ed-c2b8-4c69-926b-afba6cbd5ad0';
  $pane = new stdClass();
  $pane->pid = 'new-e8751dd9-4316-4c52-8616-f2e08476b77d';
  $pane->panel = 'middle';
  $pane->type = 'next_timesheet';
  $pane->subtype = 'next_timesheet';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = 'e8751dd9-4316-4c52-8616-f2e08476b77d';
  $display->content['new-e8751dd9-4316-4c52-8616-f2e08476b77d'] = $pane;
  $display->panels['middle'][3] = 'new-e8751dd9-4316-4c52-8616-f2e08476b77d';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['timesheet'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'timesheet_daily';
  $page->task = 'page';
  $page->admin_title = 'Timesheet daily';
  $page->admin_description = '';
  $page->path = 'timesheet/daily/!day';
  $page->access = array(
    'plugins' => array(),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array(
    'day' => array(
      'id' => 1,
      'identifier' => 'day',
      'name' => 'string',
      'settings' => array(
        'use_tail' => 0,
      ),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_timesheet_daily__panel_context_4b11efb6-f4d9-4754-9609-f0bc33d9de6d';
  $handler->task = 'page';
  $handler->subtask = 'timesheet_daily';
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
      1 => array(
        'identifier' => 'String',
        'keyword' => 'string',
        'name' => 'string',
        'string' => '%day',
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
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'day_access',
          'settings' => NULL,
          'context' => array(
            0 => 'argument_string_1',
            1 => 'relationship_timesheet_node_1',
          ),
          'not' => TRUE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'onerowtwocols';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
      'left' => NULL,
      'right' => NULL,
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
  $pane->pid = 'new-77e02012-7662-4668-a7e2-b9fdb582d474';
  $pane->panel = 'left';
  $pane->type = 'timesheet_daily_navegation';
  $pane->subtype = 'timesheet_daily_navegation';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '77e02012-7662-4668-a7e2-b9fdb582d474';
  $display->content['new-77e02012-7662-4668-a7e2-b9fdb582d474'] = $pane;
  $display->panels['left'][0] = 'new-77e02012-7662-4668-a7e2-b9fdb582d474';
  $pane = new stdClass();
  $pane->pid = 'new-70d3a00e-4785-4fba-8999-2a28ef9de33f';
  $pane->panel = 'right';
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
  $display->panels['right'][0] = 'new-70d3a00e-4785-4fba-8999-2a28ef9de33f';
  $pane = new stdClass();
  $pane->pid = 'new-d3163fdf-fef3-4d4b-a0a2-6d2124dd76f5';
  $pane->panel = 'right';
  $pane->type = 'timesheet_daily_view';
  $pane->subtype = 'timesheet_daily_view';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'd3163fdf-fef3-4d4b-a0a2-6d2124dd76f5';
  $display->content['new-d3163fdf-fef3-4d4b-a0a2-6d2124dd76f5'] = $pane;
  $display->panels['right'][1] = 'new-d3163fdf-fef3-4d4b-a0a2-6d2124dd76f5';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['timesheet_daily'] = $page;

  return $pages;

}

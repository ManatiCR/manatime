<?php
/**
 * @file
 * manatime_feature_timesheet_reminders.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function manatime_feature_timesheet_reminders_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_message_type().
 */
function manatime_feature_timesheet_reminders_default_message_type() {
  $items = array();
  $items['timesheet_reminder'] = entity_import('message_type', '{
    "name" : "timesheet_reminder",
    "description" : "Timesheet reminder",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "Please submit your timesheet.",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003EPlease submit your timesheet.\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "Hello [message:user:name]. \\r\\nWe notice you haven\\u0027t submitted your timesheet this week.\\r\\nWould you be so kind to do it as soon as possible?\\r\\nThank you so much.",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003EHello [message:user:name].\\u003Cbr \\/\\u003E\\nWe notice you haven\\u0026#039;t submitted your timesheet this week.\\u003Cbr \\/\\u003E\\nWould you be so kind to do it as soon as possible?\\u003Cbr \\/\\u003E\\nThank you so much.\\u003C\\/p\\u003E\\n"
        }
      ]
    }
  }');
  return $items;
}

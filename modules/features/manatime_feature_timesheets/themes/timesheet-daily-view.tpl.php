<?php

/**
 * @file
 * Template file for timesheet daily view.
 */
 ?>
<main id="time-entries-daily-main">
  <table class="time-time_entries-list">
    <thead>
      <tr>
        <th><?php print $table_headers['project']; ?></th>
        <th><?php print $table_headers['task']; ?></th>
        <th><?php print $table_headers['description']; ?></th>
        <th><?php print $table_headers['duration']; ?></th>
      </tr>
    </thead>
    <tbody>
      <?php if (!empty($time_entries)): ?>
        <?php foreach ($time_entries as $time_entry): ?>
          <tr class="time-entry">
            <th>
              <?php print $time_entry['project']?>
            </th>
            <th>
              <?php print $time_entry['task']?>
            </th>
            <th>
              <?php print $time_entry['description']?>
            </th>
            <th>
              <?php print $time_entry['duration']?>
            </th>
          </tr>
        <?php endforeach; ?>
      <?php endif; ?>
    <tbody>
  </table>
</main>

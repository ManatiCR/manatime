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
              <p class="time-entry--project"><?php print $time_entry['project']?></p>
            </th>
            <th>
              <p class="time-entry--task"><?php print $time_entry['task']?></p>
            </th>
            <th>
              <p class="time-entry--description"><?php print $time_entry['description']?></p>
            </th>
            <th>
              <p class="time-entry--duration"><?php print $time_entry['duration']?></p>
            </th>
          </tr>
        <?php endforeach; ?>
      <?php endif; ?>
    <tbody>
  </table>
</main>

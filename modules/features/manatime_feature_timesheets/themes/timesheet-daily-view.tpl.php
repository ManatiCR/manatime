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
        <th><?php print t('Project'); ?></th>
        <th><?php print t('Task'); ?></th>
        <th><?php print t('Description'); ?></th>
        <th><?php print t('Duration'); ?></th>
      </tr>
    </thead>
    <?php print $test; ?>
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

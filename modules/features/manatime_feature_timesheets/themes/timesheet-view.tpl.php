<?php

/**
 * @file
 * Template file for timesheet.
 */
 ?>
<aside class="time-entries-block">
  <table class="time-entries-list">
    <tr>
      <th>Description</th>
      <th>Sunday</th>
      <th>Monday</th>
      <th>Tuesday</th>
      <th>Wednesday</th>
      <th>Thursday</th>
      <th>Friday</th>
      <th>Saturday</th>
    </tr>
    <?php foreach ($records as $record): ?>
      <tr class="record--entries">
        <th>
          <p class="record--project"><?php print $record['project']?></p>
          <p class="record--task"><?php print $record['task']?></p>
        </th>
        <!-- 7: Days of the week. -->
        <?php for ($number_day = 0; $number_day < 7; $number_day++): ?>
          <?php if (isset($record['entries'][$number_day])): ?>
            <th title="<?php print $record['entries'][$number_day][0]['description']; ?>">
              <?php print $record['entries'][$number_day][0]['duration']; ?>
            </th>
          <?php else: ?>
            <th><?php print '<a title="add time entry" href="#">add</a>'; ?></th>
          <?php endif; ?>
        <?php endfor; ?>
      </tr>
    <?php endforeach; ?>
  </table>
</aside>

<?php

/**
 * @file
 * Template file for timesheet.
 */
 ?>

 <main id="time-entries-main">

   <?php print $timesheet_title ?>
   <?php if (empty($records)): ?>
     <p>Empty.</p>
   <?php else: ?>
       <table class="time-time_entries-list">
         <thead>
           <tr>
             <th><?php print t('Task'); ?></th>
             <th><?php print t('Monday'); ?></th>
             <th><?php print t('Tuesday'); ?></th>
             <th><?php print t('Wednesday'); ?></th>
             <th><?php print t('Monday'); ?></th>
             <th><?php print t('Friday'); ?></th>
             <th><?php print t('Saturday'); ?></th>
             <th><?php print t('Sunday'); ?></th>
             <th><?php print t('Total'); ?></th>
           </tr>
         </thead>
         <tbody>
           <?php foreach ($records as $record): ?>
             <tr class="record--time-entries">
               <th>
                 <p class="record--project"><?php print $record['project']?></p>
                 <p class="record--task"><?php print $record['task']?></p>
               </th>
               <!-- 7: Days of the week. -->
               <?php for ($number_day = 1; $number_day <= 7; $number_day++): ?>
                 <?php if (isset($record['time_entries'][$number_day])): ?>
                   <th>
                     <p title="<?php print $record['time_entries'][$number_day][0]['description']; ?>">
                       <?php print $record['time_entries'][$number_day][0]['duration']; ?>
                     </p>
                   </th>
                 <?php else: ?>
                   <th><?php print '<a title="Add time entry" href="#">add</a>'; ?></th>
                 <?php endif; ?>
               <?php endfor; ?>
               <th>
                 <?php print $record['total_hours_worked']; ?>
               </th>
               <th>
                 <?php print $record['remove_link_row'];?>
               </th>
             </tr>
           <?php endforeach; ?>
         <tbody>
       </table>
     <?php endif; ?>
   <?php print $add_row_link; ?>
   <?php print '<a href="timesheet/submit-timesheet/' . $timesheet_id . '/nojs" class="ctools-use-modal">' . t('Submit timesheet') . '</a>';?>
 </main>

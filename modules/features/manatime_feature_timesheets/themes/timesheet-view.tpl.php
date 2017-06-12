<?php

/**
 * @file
 * Template file for timesheet.
 */
 ?>

 <main id="time-entries-main">
   <table class="time-time_entries-list">
     <thead>
       <tr>
         <?php foreach ($table_headers as $header): ?>
           <th><?php print $header; ?></th>
         <?php endforeach; ?>
       </tr>
     </thead>
     <tbody>
       <?php if (!empty($records)): ?>
         <?php foreach ($records as $record): ?>
           <tr class="record--time-entries">
             <th>
               <p class="record--project"><?php print $record['project']?></p>
               <p class="record--task"><?php print $record['task']?></p>
             </th>
             <?php foreach ($record['time_entries'] as $entry): ?>
               <th><?php print $entry; ?></th>
             <?php endforeach; ?>
             <th>
               <?php print $record['total_hours_worked']; ?>
             </th>
             <th>
               <?php print $record['remove_link_row'];?>
             </th>
           </tr>
         <?php endforeach; ?>
       <?php endif; ?>
     <tbody>
   </table>
   <?php print $add_row_link; ?>
   <?php print $submit_link;?>
 </main>

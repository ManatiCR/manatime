<?php

/**
 * @file
 * Template file for timesheet.
 */
 ?>

 <main id="time-entries-main">
   <?php if (empty($records)): ?>
     <p>empty</p>
   <?php else: ?>
       <table class="time-time_entries-list">
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
           <tr class="record--time-entries">
             <th>
               <p class="record--project"><?php print $record['project']?></p>
               <p class="record--task"><?php print $record['task']?></p>
             </th>
             <!-- 7: Days of the week. -->
             <?php for ($number_day = 0; $number_day < 7; $number_day++): ?>
               <?php if (isset($record['time_entries'][$number_day])): ?>
                 <th>
                   <p title="<?php print $record['time_entries'][$number_day][0]['description']; ?>">
                     <?php print $record['time_entries'][$number_day][0]['duration']; ?>
                   </p>
                 </th>
               <?php else: ?>
                 <th><?php print '<a title="add time entry" href="#">add</a>'; ?></th>
               <?php endif; ?>
             <?php endfor; ?>
           </tr>
         <?php endforeach; ?>
       </table>
     <?php endif; ?>
   <?php print $add_row_link; ?>
 </main>

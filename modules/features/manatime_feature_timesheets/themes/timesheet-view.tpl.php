<?php

/**
 * @file
 * Template file for timesheet.
 */
 ?>
 <aside class="time-entries-block">
   <ul class="time-entries-list">
     <?php foreach ($records as $record): ?>
       <li>
         <p class="record--project"><?php print $record['project']?></p>
         <p class="record--task"><?php print $record['task']?></p>
           <ul class="record--entries">
             <?php foreach ($record['entries'] as $entry): ?>
               <li>
                 <?php print $entry['date']; ?>
                 <p title="<?php print $entry['description']; ?>">
                   <?php print $entry['duration']; ?>
                 </p>
               </li>
             <?php endforeach; ?>
           </ul>
       </li>
     <?php endforeach; ?>
   </ul>
</aside>

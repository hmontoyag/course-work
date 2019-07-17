import { Component, OnInit, Output, EventEmitter } from '@angular/core';
import { WAPCustomEvent } from '../../models/event.interface';
import { FormBuilder, Validators, FormGroup } from '@angular/forms';

@Component({
  selector: 'app-new-event',
  templateUrl: './new-event.component.html',
  styleUrls: ['./new-event.component.css']
})
export class NewEventComponent implements OnInit {
  currentEvent: WAPCustomEvent;
  newEventGroup: FormGroup;
  constructor(private fb: FormBuilder) {
    this.newEventGroup = this.fb.group({
      name: ['', Validators.required ],
      date: ['', Validators.required ],
    })
  }
  @Output() newEvent = new EventEmitter<WAPCustomEvent>();
  addEvent(newEvent: WAPCustomEvent) {
    newEvent = this.newEventGroup.value;
    console.log(newEvent.name);
    console.log(newEvent.date);
    this.newEvent.emit(newEvent);
  }

  ngOnInit() {
  }

}

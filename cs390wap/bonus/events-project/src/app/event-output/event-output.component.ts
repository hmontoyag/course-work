import { Component, OnInit, Input } from '@angular/core';
import { WAPCustomEvent } from '../models/event.interface';
import { NewEventComponent } from './new-event/new-event.component';

@Component({
  selector: 'app-event-output',
  templateUrl: './event-output.component.html',
  styleUrls: ['./event-output.component.css']
})
export class EventOutputComponent implements OnInit {
  events: WAPCustomEvent[];
  constructor() {
    this.events = [
      { name: 'LabEvent 1', date: new Date() },
      { name: 'LabEvent 2', date: new Date()}
    ]
  }
  
  public addEvent(newEvent: WAPCustomEvent){
    //console.log(newEvent.name);
    //console.log(newEvent.date);
    this.events.push(newEvent);
  }
  
  
  
  
  ngOnInit() {
  }

}

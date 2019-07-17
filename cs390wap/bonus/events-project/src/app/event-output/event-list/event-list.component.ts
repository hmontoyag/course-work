import { Component, OnInit, Input } from '@angular/core';
import { WAPCustomEvent } from '../../models/event.interface';

@Component({
  selector: 'app-event-list',
  templateUrl: './event-list.component.html',
  styleUrls: ['./event-list.component.css']
})
export class EventListComponent implements OnInit {
  @Input() eventList: WAPCustomEvent[];
  constructor() { }

  ngOnInit() {
  }

}

import { Component, OnInit } from '@angular/core';
import { EventState } from '../reducers/eventReducer';
import { Store } from '@ngrx/store';
import { Observable } from 'rxjs';
import { WAPCustomEvent } from '../models/event.interface';
import { AddEvent } from '../actions/event.actions';

@Component({
  selector: 'app-store',
  templateUrl: './store.component.html',
  styleUrls: ['./store.component.css']
})
export class StoreComponent implements OnInit {
  events: Observable<WAPCustomEvent[]>;

  constructor(private store: Store<EventState>) {
  }


  ngOnInit() {
  }

}

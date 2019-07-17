import { Component, OnInit } from '@angular/core';
import { Observable } from 'rxjs';
import { EventState } from '../../reducers/eventReducer';
import { Store, select } from '@ngrx/store';
import { WAPCustomEvent } from '../../models/event.interface';
import { RemoveEvent } from '../../actions/event.actions';

@Component({
  selector: 'app-store-list',
  templateUrl: './store-list.component.html',
  styleUrls: ['./store-list.component.css']
})
export class StoreListComponent implements OnInit {
  eventList$: Observable<WAPCustomEvent[]>;
  eventList: WAPCustomEvent[];
  constructor(private store: Store<EventState>) {
  }

  ngOnInit() {
  }
  removeItem(event) {
  }

}

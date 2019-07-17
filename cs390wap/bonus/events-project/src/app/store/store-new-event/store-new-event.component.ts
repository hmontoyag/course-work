import { Component, OnInit } from '@angular/core';
import { FormGroup, FormBuilder, Validators } from '@angular/forms';
import { EventState } from '../../reducers/eventReducer';
import { Store } from '@ngrx/store';
import { AddEvent, ADD_EVENT } from '../../actions/event.actions';


@Component({
  selector: 'app-store-new-event',
  templateUrl: './store-new-event.component.html',
  styleUrls: ['./store-new-event.component.css']
})
export class StoreNewEventComponent implements OnInit {
  newEventGroup: FormGroup;
  constructor(private fb: FormBuilder, private store: Store<EventState>) { 
    this.newEventGroup = this.fb.group({
      name: ['', Validators.required ],
      date: ['', Validators.required ],
    })
  }
  addEvent() {
    const eventFormValue = this.newEventGroup.value;
    let addAction = new AddEvent(eventFormValue);
    this.store.dispatch(addAction);
  }
  

  ngOnInit() {
  }

}

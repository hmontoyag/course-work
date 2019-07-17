import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { MatListModule, MatCardModule, MatDividerModule, MatInputModule, MatDatepickerModule, MatNativeDateModule, MatButtonModule } from '@angular/material';
import { FlexLayoutModule } from '@angular/flex-layout';
import { StoreModule } from '@ngrx/store';

import { AppComponent } from './app.component';
import { AppRoutingModule } from './app-routing.module';
import { HomeComponent } from './home/home.component';
import { EventOutputComponent } from './event-output/event-output.component';
import { StoreComponent } from './store/store.component';
import { EventListComponent } from './event-output/event-list/event-list.component';
import { NewEventComponent } from './event-output/new-event/new-event.component';
import { ReactiveFormsModule } from '@angular/forms';
import { eventReducer } from './reducers/eventReducer';
import { StoreListComponent } from './store/store-list/store-list.component';
import { StoreNewEventComponent } from './store/store-new-event/store-new-event.component';

@NgModule({
  declarations: [
    AppComponent,
    HomeComponent,
    EventListComponent,
    EventOutputComponent,
    StoreComponent,
    NewEventComponent,
    StoreListComponent,
    StoreNewEventComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    MatListModule,
    MatDividerModule,
    MatInputModule,
    MatCardModule,
    MatDatepickerModule,
    MatNativeDateModule,
    MatButtonModule,
    ReactiveFormsModule,
    FlexLayoutModule,
    BrowserAnimationsModule,
    StoreModule.forRoot({ //sets up the centralized piece of state
      events: eventReducer // for the events property of the state, send state to the eventReducer
    })
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }

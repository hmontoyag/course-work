import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { StoreNewEventComponent } from './store-new-event.component';

describe('StoreNewEventComponent', () => {
  let component: StoreNewEventComponent;
  let fixture: ComponentFixture<StoreNewEventComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ StoreNewEventComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(StoreNewEventComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

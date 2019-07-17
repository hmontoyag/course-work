import * as fromActions from '../actions/event.actions';
import { WAPCustomEvent } from '../models/event.interface';
const initialState = [];
//function to duplicate array
function duplicateArray(arr): any[] {
    return JSON.parse(JSON.stringify(arr));
}
export interface EventState {
  events: WAPCustomEvent[];
}

export function eventReducer(state: WAPCustomEvent[] = initialState, action: fromActions.EventActions) {
    switch (action.type) {
      case fromActions.ADD_EVENT:
        //be sure to create a copy of the state and add a new item to it.
        state = duplicateArray(state);
        state.push(action.payload);
        console.log(action.payload);
        console.log(state);
        return state;
  
      case fromActions.REMOVE_EVENT:
        //be sure to create a copy of the state and remove the item specified.
        return state;

      default:
        return state;
    }
  }

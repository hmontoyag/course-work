import { Action } from '@ngrx/store';
import { WAPCustomEvent } from '../models/event.interface';
export const ADD_EVENT = 'ADD_EVENT';
export const REMOVE_EVENT = 'REMOVE_EVENT';
export const GET_EVENTS = 'GET_EVENTS';
export class AddEvent implements Action {
    readonly type = ADD_EVENT;
    constructor(public payload: WAPCustomEvent) {}
}
export class RemoveEvent implements Action {
    readonly type = REMOVE_EVENT;
    constructor(public payload: WAPCustomEvent) {}
}
export class GetEvents implements Action {
    readonly type = GET_EVENTS;
    constructor() {}
}
export type EventActions = AddEvent | RemoveEvent;
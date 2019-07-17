import { Injectable } from '@angular/core';
import {HttpClientModule} from '@angular/common/http';
import { HttpClient } from '@angular/common/http';


@Injectable({
  providedIn: 'root',
  
})



export class MovieUtilService {

  constructor(private http: HttpClient) { }

  //Makes an HTTP GET to http://localhost:3000/movies
  getMovies(){ 
    return this.http.get('http://localhost:3000/movies');

  }


  //Makes an HTTP GET to http://localhost:3000/movies?q=<query>
  search(query){
    return this.http.get('http://localhost:3000/movies?q='+query+'');
   }

}

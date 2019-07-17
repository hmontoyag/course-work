import { Component, OnInit } from '@angular/core';
import { Movie } from '../models/movie.interface';
import { FormControl } from '@angular/forms';
import  {MovieUtilService } from '../movie-util.service';
import { HttpClient } from '@angular/common/http';
import { from } from 'rxjs';
import {distinctUntilChanged, debounceTime, filter, distinct } from 'rxjs/operators';

@Component({
  selector: 'app-movie-list',
  templateUrl: './movie-list.component.html',
  styleUrls: ['./movie-list.component.css']
})
export class MovieListComponent implements OnInit {
  movies: Movie[];
  searchControl: FormControl;
  constructor(private MovieUtilService: MovieUtilService, private HttpClient: HttpClient) {
    this.MovieUtilService.getMovies().subscribe(data => this.movies = <Movie[]> data, error => {error = error, this.movies = []} );
    this.searchControl = new FormControl();
    /* set up movies data and search here */
    /* Note: this.searchControl.valueChanges returns a Observable<string> */
     /* this.searchControl.valueChanges.pipe(
      debounceTime(400), distinctUntilChanged(),
     
      ).subscribe(char=> console.log(char));*/

      this.searchControl.valueChanges.pipe(
        debounceTime(400), distinctUntilChanged()
      ).subscribe(data =>  {console.log(data),this.boop(data)}, error =>  error = error );
  }
  boop(query){
 
    
 this.MovieUtilService.search(query).subscribe(data => this.movies = <Movie[]> data, error =>  {error = error, this.movies = []} );
  
  }
  ngOnInit() {
  }

}

import { Component, OnInit } from '@angular/core';
import { Movie } from '../../shared/models/movie.interface';
import { MovieUtilService } from '../../shared/movie-util.service';


@Component({
  selector: 'cs390wap-movie-list',
  templateUrl: './movie-list.component.html',
  styleUrls: ['./movie-list.component.css']
})
export class MovieListComponent implements OnInit {
  movies: Movie[];
  constructor(private movieUtilService: MovieUtilService) { 
    this.movies = this.movieUtilService.getMovies();
   }
  
  ngOnInit() {
  }

}

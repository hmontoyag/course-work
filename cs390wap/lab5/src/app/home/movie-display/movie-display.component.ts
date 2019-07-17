import { Component, OnInit } from '@angular/core';
import { Movie } from '../../shared/models/movie.interface';
import { MovieUtilService } from '../../shared/movie-util.service';

@Component({
  selector: 'cs390wap-movie-display',
  templateUrl: './movie-display.component.html',
  styleUrls: ['./movie-display.component.css']
})
export class MovieDisplayComponent implements OnInit {

  movies: Movie[];
  constructor(private movieUtilService: MovieUtilService) { 
    this.movies = this.movieUtilService.getMovies();
   }

  ngOnInit() {
    console.log(this.movies[0].title)
  }

}

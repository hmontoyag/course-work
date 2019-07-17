import { Component, OnInit, Input } from '@angular/core';
import { MovieUtilService } from '../shared/movie-util.service';
import { Movie } from '../shared/models/movie.interface';

@Component({
  selector: 'cs390wap-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})


export class HomeComponent implements OnInit {
 // @Input() currentMovie: Movie;
  movies: Movie[];
  user = {
    name: 'Mary'
  }
  
  constructor(private movieUtilService: MovieUtilService) { 
   this.movies = this.movieUtilService.getMovies();
  }

  ngOnInit() {
    //console.log(this.movies[0].title)
  }

}

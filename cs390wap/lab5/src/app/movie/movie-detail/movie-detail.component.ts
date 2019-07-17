import { Component, OnInit, ChangeDetectionStrategy, Input } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { Movie } from '../../shared/models/movie.interface';
import { MovieUtilService } from '../../shared/movie-util.service';

@Component({
  selector: 'cs390wap-movie-detail',
  templateUrl: './movie-detail.component.html',
  styleUrls: ['./movie-detail.component.css']
})
export class MovieDetailComponent implements OnInit {
 // @Input() movies: Movie[];
  movie: Movie;
  constructor(private route: ActivatedRoute, private movieUtilService: MovieUtilService) {
    const movieId = +this.route.snapshot.params['id'];
    this.movie = movieUtilService.getMovie(movieId);
  }
  

  ngOnInit() {
    
  }

}

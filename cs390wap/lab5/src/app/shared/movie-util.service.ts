import { Injectable } from '@angular/core';
import { Movie, PRODUCTION_STATUS } from './models/movie.interface';
import { SharedModule } from './shared.module';

@Injectable({
  providedIn: SharedModule
})
export class MovieUtilService {
  private movies: Movie[] = [
    { 
      title: 'Uncharted',
      productionStatus: PRODUCTION_STATUS.PRE_PRODUCTION,
      genre: 'Action',
      logline: 'Plot is unknown at this time',
      tags: ['Action', 'Adventure'],
      id: 0
    },
    {
      title: 'Son of Jeru',
      productionStatus: PRODUCTION_STATUS.SCREENPLAY_FINISHED,
      genre: 'Action',
      director: 'Maneesh Tewani',
      screenwriters: [ 'Maneesh Tewani' ],
      logline: 'Unable to stop the world from ending, young Nelson unravels the troubled path to finding his parents again.',
      tags: [ 'Action', 'Drama' ],
      id: 1
    }
    
  ];
  constructor() { }
  /*
    Accepts: id as a number
    Returns: movie at an index
  */
  getMovie(id: number): Movie { 
    if(id>this.movies.length||id<0||id===undefined){
      return undefined;
    } else {
      return this.movies[id];
    }      
  }
  /*
    Accepts: movie as a Movie type
    Returns: void, updates movie at id with passed in movie
  */
  update(movie: Movie) {
    if(movie==undefined){
      return undefined;
    }
    let id = movie.id;
    if(id>this.movies.length||id<0||id===undefined){
      return undefined;
    } else {
      this.movies[id] = movie;
    }

  }
  getProductionStatuses(): string[] {
    return Object.values(PRODUCTION_STATUS);
  }
  /*
    Accepts: movie as a Movie type
    Returns: void, adds movie to the end of movies array
  */
  addMovie(movie: Movie) { 
    if(movie==undefined){
      return undefined;
    }
    movie.id = this.movies.length;
    this.movies[this.movies.length] = movie;

  }
  /*
    Accepts: void
    Returns: copy of movies
  */
  getMovies() {
   return JSON.parse(JSON.stringify(this.movies));
   /*let copy: Movie[];
   for(let i=0;i!=this.movies.length;i++){
     copy[i]=this.movies[i];
   }
   return copy;*/
  }

}

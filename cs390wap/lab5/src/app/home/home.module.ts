import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { MovieListComponent } from './movie-list/movie-list.component';
import { MovieDisplayComponent } from './movie-display/movie-display.component';
import { HomeComponent } from './home.component';
import { RouterModule } from '@angular/router';



@NgModule({
  imports: [
    CommonModule,
    RouterModule
  ],
  declarations: [
    HomeComponent,
    MovieDisplayComponent
  ]
})
export class HomeModule { }

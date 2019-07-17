import { TestBed } from '@angular/core/testing';

import { MovieUtilService } from './movie-util.service';

describe('MovieUtilService', () => {
  beforeEach(() => TestBed.configureTestingModule({}));

  it('should be created', () => {
    const service: MovieUtilService = TestBed.get(MovieUtilService);
    expect(service).toBeTruthy();
  });
});

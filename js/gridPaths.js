function gridPaths() {
    const gridSize = 20;
    let grid = [];
    //initialize grid
    for (let i = 0; i < gridSize+1; i++) {
        grid.push(new Array(gridSize+1).fill(0));
    }
    //initialize boundary conditions
    for (let i = 0; i < gridSize+1; i++) {
        grid[gridSize][i] = 1;
        grid[i][gridSize] = 1;
    }
    //dest node is 0
    grid[gridSize][gridSize] = 0;
    for (let i = gridSize-1; i >= 0; i--) {
        for (let j = gridSize-1; j >= 0; j--) {
            grid[i][j] = grid[i+1][j] + grid[i][j+1];
            console.log(grid[i][j]);
        }
    }
}

gridPaths();
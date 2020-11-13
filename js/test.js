const readLib = require('readline');

const readline = readLib.createInterface({
  input: process.stdin,
  output: process.stdout
});

readline.question("What's your name?", name => {
  console.log(`Hi ${name}!`);
  readline.close();
});

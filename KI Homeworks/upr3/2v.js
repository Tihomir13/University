const letters = ['a', 'b'];
const numbers = ['0', '1'];

function isNameValid(string) {
  let isValid = false;

  if (letters.includes(string[0])) {
    isValid = true;
  } else {
    console.log(`The constant is not valid`);
    return;
  }

  for (let i = 1; i < string.length; i++) {
    const combinedSymbols = [...numbers, ...letters];

    if (combinedSymbols.includes(string[i])) {
    } else {
      isValid = false;
      break;
    }
  }

  console.log(`The constant is ${isValid ? 'valid' : 'not valid'}`);
}

isNameValid('aaa222');

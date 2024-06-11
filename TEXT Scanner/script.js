const titleText = "Image To Text";
const descriptionText = "Convert images to editable text with our powerful OCR technology.";

const title = document.querySelector(".title");
const description = document.querySelector(".description");

let titleIndex = 0;
let descriptionIndex = 0;

function typeTitle() {
  if (titleIndex < titleText.length) {
    title.textContent += titleText.charAt(titleIndex);
    titleIndex++;
    setTimeout(typeTitle, 100); // Adjust the speed by changing the timeout value
  }
}

function typeDescription() {
  if (descriptionIndex < descriptionText.length) {
    description.textContent += descriptionText.charAt(descriptionIndex);
    descriptionIndex++;
    setTimeout(typeDescription, 50); // Adjust the speed by changing the timeout value
  }
}

typeTitle();
setTimeout(typeDescription, 1000); // Delay before starting the description typing
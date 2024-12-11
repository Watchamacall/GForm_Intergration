// Select all toggle buttons
const toggleButtons = document.querySelectorAll('.toggle-btn');

// Add click event listener to each button
toggleButtons.forEach((button) => {
    button.addEventListener('click', () => {
        // Find the next sibling image for the clicked button and toggle visibility
        const image = button.nextElementSibling;
        if (image.style.display === 'block') {
            image.style.display = 'none';
        } else {
            image.style.display = 'block';
        }
    });
});
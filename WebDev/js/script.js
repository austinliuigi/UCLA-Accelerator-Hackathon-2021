jokePunchline = document.getElementById("joke_punchline")
jokeSetup = document.getElementById("joke_setup")

$("button").click(function () {
    $.get("https://official-joke-api.appspot.com/random_joke", function (data, status) {
        jokeSetup.innerHTML = data.setup
        jokePunchline.innerHTML = "> " + data.punchline
    });
});

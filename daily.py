import requests
import getpass
from datetime import datetime
import locale

locale.setlocale(locale.LC_TIME, 'fr_FR.utf8')

def send_to_discord(webhook_url, tasks, username):
    date_str = datetime.now().strftime("%d %B %Y")
    message = f"{date_str}:\n"
    for task in tasks:
        message += f"- [ ] {task}\n"

    payload = {
        "content": message,
        "username": username.title(),
    }
    response = requests.post(webhook_url, json=payload)
    return response.status_code


def main():
    tasks = []
    while True:
        task = input("Entrez une tâche (tapez 'end' pour terminer) : ")
        if task.lower() == "end":
            break
        tasks.append(task)

    username = getpass.getuser()
    webhook_url = "https://discordapp.com/api/webhooks/1184435859316019220/Ryk7ct_EBX4PdZdParN8vjxyG5UjRAHrZasjbfV_J8Vldxg_dducyZfdtxLdZ2NBLcSs"
    status = send_to_discord(webhook_url, tasks, username)
    if status == 204:
        print("Tâches envoyées avec succès !")
    else:
        print("Erreur lors de l'envoi des tâches.")


if __name__ == "__main__":
    main()

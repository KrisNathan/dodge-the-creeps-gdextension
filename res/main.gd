extends Main

func _on_mob_timer_timeout():
	on_MobTimer_timeout()


func _on_score_timer_timeout():
	on_ScoreTimer_timeout()


func _on_start_timer_timeout():
	on_StartTimer_timeout()


func _on_hud_start_game():
	new_game()
